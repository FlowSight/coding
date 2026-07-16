#!/usr/bin/env node
// ============================================================
// browser_fetch.js — Generates the Playwright code to run in
//                    VS Code Simple Browser for fetching data.
//
// Usage: node Progress/coding/tools/leetcode/browser_fetch.js
//        → prints the code to paste/run via Copilot browser tools
//
// This is the SOURCE OF TRUTH for the browser fetch logic.
// Never write ad-hoc fetch code — always use this.
// ============================================================
'use strict';

const fs = require('fs');
const path = require('path');

const CONFIG = JSON.parse(fs.readFileSync(path.join(__dirname, 'config.json'), 'utf8'));
const CACHE_FILE = path.join(__dirname, '.lc_cache.json');
const cutoffTs = Math.floor(new Date(CONFIG.cutoff_date).getTime() / 1000);

// This is the code that runs inside page.evaluate()
const BROWSER_CODE = `
const MAY_CUTOFF = ${cutoffTs};
const result = await page.evaluate(async (CUTOFF) => {
  const allSubs = [];
  const seen = new Set();
  let offset = 0;
  let keepGoing = true;
  let pages = 0;
  const MAX_PAGES = 200;

  // Step 1: Fetch all accepted submissions after cutoff
  while (keepGoing && pages < MAX_PAGES) {
    const query = \\\`query submissionList($offset: Int!, $limit: Int!) {
      submissionList(offset: $offset, limit: $limit) {
        hasNext submissions { title titleSlug statusDisplay timestamp lang }
      }
    }\\\`;
    const res = await fetch('https://leetcode.com/graphql', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ query, variables: { offset, limit: 50 } })
    });
    if (!res.ok) { await new Promise(r => setTimeout(r, 3000)); continue; }
    const data = await res.json();
    const list = data.data?.submissionList;
    if (!list?.submissions?.length) break;
    for (const s of list.submissions) {
      const ts = parseInt(s.timestamp);
      if (ts < CUTOFF) { keepGoing = false; break; }
      if (s.statusDisplay === 'Accepted' && !seen.has(s.titleSlug)) {
        seen.add(s.titleSlug);
        allSubs.push({ title: s.title, slug: s.titleSlug, lang: s.lang,
          date: new Date(ts * 1000).toISOString().split('T')[0], timestamp: ts });
      }
    }
    if (keepGoing && list.hasNext) { offset += 50; pages++; await new Promise(r => setTimeout(r, 800)); }
    else if (!list.hasNext) keepGoing = false;
  }

  // Step 2: Fetch problem details for all unique slugs
  const details = {};
  for (let i = 0; i < allSubs.length; i += 5) {
    const batch = allSubs.slice(i, i + 5);
    const promises = batch.map(async (sub) => {
      const q = \\\`query questionData($titleSlug: String!) {
        question(titleSlug: $titleSlug) { questionFrontendId title difficulty topicTags { name } }
      }\\\`;
      const r = await fetch('https://leetcode.com/graphql', {
        method: 'POST', headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ query: q, variables: { titleSlug: sub.slug } })
      });
      const d = await r.json();
      const qd = d.data?.question;
      if (qd) details[sub.slug] = {
        lcNum: qd.questionFrontendId, title: qd.title, difficulty: qd.difficulty,
        tags: (qd.topicTags || []).map(t => t.name)
      };
    });
    await Promise.all(promises);
    if (i + 5 < allSubs.length) await new Promise(r => setTimeout(r, 500));
  }

  return { submissions: allSubs, details, fetchedAt: new Date().toISOString() };
}, MAY_CUTOFF);

return JSON.stringify(result);
`;

// Check if cache already exists
if (fs.existsSync(CACHE_FILE)) {
  const stat = fs.statSync(CACHE_FILE);
  const age = (Date.now() - stat.mtimeMs) / 1000 / 60;
  console.log(`⚠️  Cache already exists (${Math.round(age)} min old). Delete it first or run init.js directly.\n`);
  console.log(`   rm ${CACHE_FILE}`);
  process.exit(0);
}

console.log('═══════════════════════════════════════════════');
console.log(' LeetCode Browser Fetch — copy this to Copilot');
console.log('═══════════════════════════════════════════════');
console.log('');
console.log('Ask Copilot to run this in the authenticated LeetCode browser:');
console.log('');
console.log('───── START ─────');
console.log(BROWSER_CODE);
console.log('───── END ─────');
console.log('');
console.log('Then save the output as:');
console.log(`  ${CACHE_FILE}`);
console.log('');
console.log('Then run:');
console.log('  node Progress/coding/tools/leetcode/init.js');
