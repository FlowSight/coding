#!/usr/bin/env node
// ============================================================
// sync.js — Incremental sync since last run
// ============================================================
// Same pipeline as init but only fetches new submissions.
// Also re-verifies tracker problems (catches pagination gaps).
// ============================================================
'use strict';

const fs = require('fs');
const {
  loadConfig, loadState, saveState, getSession,
  fetchSubmissions, fetchProblemDetails, verifySolved,
  hasCache, loadCache, clearCache,
  updateGlobalXlsx, extractMdLcNumbers, processTracker,
  sleep,
} = require('./common');

async function main() {
  const config = loadConfig();
  const state = loadState();

  if (!state.lastSyncTs) {
    console.error('❌ No previous sync. Run init.js first.');
    process.exit(1);
  }

  let submissions, details;
  const lastDate = new Date(state.lastSyncTs * 1000).toISOString().split('T')[0];

  if (hasCache()) {
    console.log(`\n🔄 Sync — browser-cache (last: ${lastDate})\n`);
    const cached = loadCache(config.langFilter);
    submissions = cached.submissions.filter(s => s.timestamp > state.lastSyncTs);
    details = cached.details;
    console.log(`  ${submissions.length} new since last sync`);
  } else {
    const session = getSession();
    console.log(`\n🔄 Sync — API (since ${lastDate})\n`);
    const allSubs = await fetchSubmissions(session, state.lastSyncTs);
    submissions = allSubs.filter(s => s.lang === config.langFilter);
    console.log(`  ${submissions.length} new ${config.langFilter}`);
    if (submissions.length > 0) {
      details = await fetchProblemDetails(session, submissions.map(s => s.slug));
    } else {
      details = new Map();
    }
  }

  // Build solved set
  const solvedLcSet = new Set();
  for (const [slug, info] of details) {
    if (info.status === 'ac' || submissions.find(s => s.slug === slug)) {
      solvedLcSet.add(info.lcNum);
    }
  }

  // Also verify all remaining tracker problems (catches pagination gaps)
  if (!hasCache()) {
    const session = getSession();
    for (const t of config.trackers) {
      if (!fs.existsSync(t.mdPath)) continue;
      const mdLcNums = extractMdLcNumbers(t.mdPath);
      const unverified = mdLcNums.filter(lc => !solvedLcSet.has(lc));
      if (unverified.length > 0) {
        console.log(`\n🔍 Verifying ${unverified.length} tracker problems...`);
        const Q = `query($f:QuestionListFilterInput){problemsetQuestionList:questionList(categorySlug:"",limit:1,skip:0,filters:$f){questions:data{titleSlug questionFrontendId status}}}`;
        for (const lc of unverified) {
          try {
            const d = await (await fetch('https://leetcode.com/graphql', {
              method: 'POST', headers: { 'Content-Type': 'application/json',
                'Cookie': `LEETCODE_SESSION=${session}`, 'Referer': 'https://leetcode.com' },
              body: JSON.stringify({ query: Q, variables: { f: { searchKeywords: lc } } })
            })).json();
            const qs = d.data?.problemsetQuestionList?.questions || [];
            const match = qs.find(q => q.questionFrontendId === lc);
            if (match && match.status === 'ac') solvedLcSet.add(lc);
          } catch {}
          await sleep(300);
        }
      }
    }
  }

  // Step 1: Global XLSX
  if (submissions.length > 0) {
    console.log('\n📊 Updating Global_tracker.XLSX...');
    const globalProblems = submissions.map(s => {
      const info = details.get(s.slug);
      if (!info) return null;
      return { lc: info.lcNum, title: info.title, difficulty: info.difficulty,
               tags: (info.tags||[]).slice(0,2).join(' | '), date: s.date };
    }).filter(Boolean);
    const r = updateGlobalXlsx(config.globalXlsxPath, globalProblems);
    console.log(`  Added: ${r.added}`);
  }

  // Step 2: Trackers
  for (const t of config.trackers) {
    if (!fs.existsSync(t.mdPath)) continue;
    console.log(`\n📝 ${t.name}...`);
    const result = processTracker(t, solvedLcSet);
    if (result.matched.length > 0) {
      console.log(`  Removed ${result.removed} from MD, +${result.excelAdded} to Excel:`);
      for (const m of result.matched) console.log(`    ✅ LC ${m.lc} — ${m.title}`);
    } else {
      console.log('  Up to date.');
    }
  }

  // Save state
  const maxTs = submissions.length > 0
    ? Math.max(state.lastSyncTs, ...submissions.map(s => s.timestamp))
    : state.lastSyncTs;
  saveState({ lastSyncTs: maxTs, lastSyncDate: new Date().toISOString() });
  if (hasCache()) { clearCache(); }

  console.log('\n── Sync complete ────────────────────────\n');
}

main().catch(err => { console.error('\n❌', err.message); process.exit(1); });
