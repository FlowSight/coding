#!/usr/bin/env node
// ============================================================
// init.js — Full backfill from LeetCode into Global XLSX + trackers
// ============================================================
// Pipeline:
//   1. Fetch all accepted submissions (pagination + gap-fill)
//   2. Update Global_tracker.XLSX
//   3. For each tracker: remove solved from MD, add to company Excel
// ============================================================
'use strict';

const fs = require('fs');
const {
  loadConfig, saveState, getSession,
  fetchSubmissions, fetchProblemDetails, verifySolved,
  hasCache, loadCache, clearCache,
  updateGlobalXlsx, extractMdLcNumbers, processTracker,
  sleep,
} = require('./common');

async function main() {
  const config = loadConfig();
  let submissions, details;

  if (hasCache()) {
    // ── Browser-cache mode ──
    console.log('\n🔄 Init — browser-cache mode\n');
    const cached = loadCache(config.langFilter);
    submissions = cached.submissions;
    details = cached.details;
  } else {
    // ── Direct API mode ──
    const session = getSession();
    console.log(`\n🔄 Init — fetching from LeetCode API\n`);

    // Step A: Paginated fetch
    const allSubs = await fetchSubmissions(session, config.cutoffTs);
    submissions = allSubs.filter(s => s.lang === config.langFilter);
    console.log(`  ${submissions.length} ${config.langFilter} (${allSubs.length - submissions.length} other langs skipped)`);

    // Step B: Fetch details
    const slugs = submissions.map(s => s.slug);
    details = await fetchProblemDetails(session, slugs);

    // Step C: Gap-fill — check tracker problems that pagination missed
    console.log('\n🔍 Verifying tracker problems (gap-fill)...');
    for (const t of config.trackers) {
      if (!fs.existsSync(t.mdPath)) continue;
      const mdLcNums = extractMdLcNumbers(t.mdPath);
      // Find LC#s in tracker that we didn't already fetch
      const fetchedLcNums = new Set([...details.values()].map(d => d.lcNum));
      const missing = mdLcNums.filter(lc => !fetchedLcNums.has(lc));
      if (missing.length > 0) {
        console.log(`  ${t.name}: checking ${missing.length} problems not in pagination...`);
        // Build slugs from LC# (need to query them)
        const missingDetails = await fetchProblemDetails(session,
          missing.map(lc => null).filter(Boolean)); // Can't get slugs from LC#...
        // Alternative: verify by querying each LC# directly
        // We'll use the problemsetQuestionList approach
        const Q = `query($s:String!){question(titleSlug:$s){questionFrontendId title difficulty status topicTags{name}}}`;
        // Actually, we can't easily go from LC# to slug without another query.
        // Instead, use the status check on each problem in the tracker.
      }
    }
  }

  if (!submissions || submissions.length === 0) {
    console.log('Nothing to process.');
    return;
  }

  // Build solved LC# set from details
  const solvedLcSet = new Set();
  for (const [slug, info] of details) {
    if (info.status === 'ac' || submissions.find(s => s.slug === slug)) {
      solvedLcSet.add(info.lcNum);
    }
  }

  // ── Step 1: Update Global XLSX ──
  console.log('\n📊 Step 1: Updating Global_tracker.XLSX...');
  const globalProblems = submissions.map(s => {
    const info = details.get(s.slug);
    if (!info) return null;
    return { lc: info.lcNum, title: info.title, difficulty: info.difficulty,
             tags: (info.tags||[]).slice(0,2).join(' | '), date: s.date };
  }).filter(Boolean);
  const globalResult = updateGlobalXlsx(config.globalXlsxPath, globalProblems);
  console.log(`  Added: ${globalResult.added}`);

  // ── Step 2: Process per-company trackers ──
  for (let i = 0; i < config.trackers.length; i++) {
    const t = config.trackers[i];
    console.log(`\n📝 Step ${i+2}: ${t.name}...`);
    if (!fs.existsSync(t.mdPath)) { console.log('  ⚠️ MD not found, skipped'); continue; }

    // Also verify tracker problems directly (gap-fill for pagination misses)
    const mdLcNums = extractMdLcNumbers(t.mdPath);
    const unverified = mdLcNums.filter(lc => !solvedLcSet.has(lc));
    if (unverified.length > 0 && !hasCache()) {
      console.log(`  Verifying ${unverified.length} tracker problems via API...`);
      const session = getSession();
      // Query each by constructing slug from title (not ideal) - use problemset API instead
      const Q = `query questionList($f:QuestionListFilterInput){problemsetQuestionList:questionList(categorySlug:"",limit:1,skip:0,filters:$f){questions:data{titleSlug questionFrontendId status}}}`;
      for (const lc of unverified) {
        try {
          const d = await (await fetch('https://leetcode.com/graphql', {
            method: 'POST', headers: { 'Content-Type': 'application/json',
              'Cookie': `LEETCODE_SESSION=${getSession()}`, 'Referer': 'https://leetcode.com' },
            body: JSON.stringify({ query: Q, variables: { f: { searchKeywords: lc } } })
          })).json();
          const qs = d.data?.problemsetQuestionList?.questions || [];
          const match = qs.find(q => q.questionFrontendId === lc);
          if (match && match.status === 'ac') {
            solvedLcSet.add(lc);
          }
        } catch {}
        await sleep(300);
      }
    }

    const result = processTracker(t, solvedLcSet);
    if (result.matched.length > 0) {
      console.log(`  Removed ${result.removed} from MD, +${result.excelAdded} to Excel:`);
      for (const m of result.matched) console.log(`    ✅ LC ${m.lc} — ${m.title}`);
    } else {
      console.log('  No solved problems found in tracker.');
    }
  }

  // ── Save state ──
  const maxTs = submissions.length > 0 ? Math.max(...submissions.map(s => s.timestamp)) : 0;
  saveState({ lastSyncTs: maxTs, lastSyncDate: new Date().toISOString() });
  if (hasCache()) { clearCache(); console.log('\n  Cache cleared.'); }

  console.log('\n── Done ─────────────────────────────────\n');
}

main().catch(err => { console.error('\n❌', err.message); process.exit(1); });
