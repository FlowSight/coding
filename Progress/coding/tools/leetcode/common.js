// ============================================================
// common.js — LeetCode API + Global XLSX + MD tracker utilities
// ============================================================
// Pipeline: LeetCode → Global XLSX → per-company (MD remove + Excel add)
// ============================================================
'use strict';

const fs = require('fs');
const path = require('path');
const { execSync } = require('child_process');

const ROOT_DIR = path.resolve(__dirname, '../../../..');
const STATE_FILE = path.join(__dirname, '.lc_state.json');
const CONFIG_FILE = path.join(__dirname, 'config.json');
const CACHE_FILE = path.join(__dirname, '.lc_cache.json');

// ─── Config & State ─────────────────────────────────────────

function loadConfig() {
  const raw = JSON.parse(fs.readFileSync(CONFIG_FILE, 'utf8'));
  return {
    username: raw.username,
    cutoffTs: Math.floor(new Date(raw.cutoff_date).getTime() / 1000),
    langFilter: raw.lang_filter,
    globalXlsxPath: path.join(ROOT_DIR, raw.global_xlsx),
    trackers: (raw.trackers || [])
      .filter(t => t.enabled !== false)
      .map(t => ({
        name: t.name,
        mdPath: path.join(ROOT_DIR, t.path),
        excelPath: t.excel ? path.join(ROOT_DIR, t.excel) : null,
      })),
  };
}

function loadState() {
  if (!fs.existsSync(STATE_FILE)) return { lastSyncTs: 0 };
  return JSON.parse(fs.readFileSync(STATE_FILE, 'utf8'));
}

function saveState(state) {
  fs.writeFileSync(STATE_FILE, JSON.stringify(state, null, 2) + '\n');
}

// ─── Session ────────────────────────────────────────────────

function getSession() {
  if (process.env.LEETCODE_SESSION) return process.env.LEETCODE_SESSION;
  const envFile = path.join(__dirname, '.env');
  if (fs.existsSync(envFile)) {
    const match = fs.readFileSync(envFile, 'utf8').match(/LEETCODE_SESSION=(.+)/);
    if (match) return match[1].trim();
  }
  throw new Error('LEETCODE_SESSION not set. Use browser-cache mode or set env var.');
}

// ─── LeetCode GraphQL ───────────────────────────────────────

const LC_GQL = 'https://leetcode.com/graphql';
function sleep(ms) { return new Promise(r => setTimeout(r, ms)); }

function lcHeaders(session) {
  return { 'Content-Type': 'application/json', 'Cookie': `LEETCODE_SESSION=${session}`,
           'Referer': 'https://leetcode.com', 'Origin': 'https://leetcode.com' };
}

async function gql(session, query, variables) {
  let res = await fetch(LC_GQL, { method: 'POST', headers: lcHeaders(session),
    body: JSON.stringify({ query, variables }) });
  if (!res.ok) {
    await sleep(3000);
    res = await fetch(LC_GQL, { method: 'POST', headers: lcHeaders(session),
      body: JSON.stringify({ query, variables }) });
    if (!res.ok) throw new Error(`GraphQL ${res.status}`);
  }
  return res.json();
}

/** Paginated submission fetch (API caps at ~1300 offset). */
async function fetchSubmissions(session, fromTs) {
  const Q = `query($o:Int!,$l:Int!){submissionList(offset:$o,limit:$l){hasNext submissions{title titleSlug statusDisplay timestamp lang}}}`;
  const results = [], seen = new Set();
  let offset = 0, go = true;
  process.stdout.write('Fetching submissions');
  while (go) {
    const d = await gql(session, Q, { o: offset, l: 50 });
    const list = d.data?.submissionList;
    if (!list?.submissions?.length) break;
    for (const s of list.submissions) {
      const ts = parseInt(s.timestamp);
      if (ts < fromTs) { go = false; break; }
      if (s.statusDisplay === 'Accepted' && !seen.has(s.titleSlug)) {
        seen.add(s.titleSlug);
        results.push({ title: s.title, slug: s.titleSlug, lang: s.lang,
          date: new Date(ts * 1000).toISOString().split('T')[0], timestamp: ts });
      }
    }
    if (go && list.hasNext) { offset += 50; process.stdout.write('.'); await sleep(800); }
    else go = false;
  }
  console.log(` ${results.length} found`);
  return results;
}

/** Fetch details for slugs. */
async function fetchProblemDetails(session, slugs) {
  const Q = `query($s:String!){question(titleSlug:$s){questionFrontendId title difficulty status topicTags{name}}}`;
  const details = new Map();
  process.stdout.write(`Details for ${slugs.length} problems`);
  for (let i = 0; i < slugs.length; i += 5) {
    const batch = slugs.slice(i, i + 5);
    await Promise.all(batch.map(async slug => {
      const d = await gql(session, Q, { s: slug });
      const q = d.data?.question;
      if (q) details.set(slug, { lcNum: q.questionFrontendId, title: q.title,
        difficulty: q.difficulty, status: q.status, tags: (q.topicTags||[]).map(t=>t.name) });
    }));
    process.stdout.write('.');
    if (i + 5 < slugs.length) await sleep(500);
  }
  console.log(' done');
  return details;
}

/**
 * Verify solve status for specific LC slugs (fills pagination gaps).
 * Returns array of solved problem info.
 */
async function verifySolved(session, slugs) {
  const Q = `query($s:String!){question(titleSlug:$s){questionFrontendId title difficulty status topicTags{name}}}`;
  const solved = [];
  for (let i = 0; i < slugs.length; i += 5) {
    const batch = slugs.slice(i, i + 5);
    await Promise.all(batch.map(async slug => {
      const d = await gql(session, Q, { s: slug });
      const q = d.data?.question;
      if (q && q.status === 'ac') {
        solved.push({ slug, lcNum: q.questionFrontendId, title: q.title,
          difficulty: q.difficulty, tags: (q.topicTags||[]).map(t=>t.name) });
      }
    }));
    if (i + 5 < slugs.length) await sleep(500);
  }
  return solved;
}

// ─── Cache (browser-fetched) ────────────────────────────────

function hasCache() { return fs.existsSync(CACHE_FILE); }

function loadCache(langFilter) {
  const raw = JSON.parse(fs.readFileSync(CACHE_FILE, 'utf8'));
  const subs = langFilter ? raw.submissions.filter(s => s.lang === langFilter) : raw.submissions;
  const details = new Map(Object.entries(raw.details));
  console.log(`Cache: ${subs.length} ${langFilter||'all'} subs, ${details.size} details`);
  return { submissions: subs, details };
}

function clearCache() { if (fs.existsSync(CACHE_FILE)) fs.unlinkSync(CACHE_FILE); }

// ─── Global XLSX ────────────────────────────────────────────

/**
 * Add new problems to Global_tracker.XLSX. Returns { added }.
 */
function updateGlobalXlsx(xlsxPath, problems) {
  // problems: [{ lc, title, difficulty, tags, date }]
  const pyData = JSON.stringify(problems);
  const script = `
import openpyxl, re, json, sys
data = json.loads(sys.stdin.read())
wb = openpyxl.load_workbook(sys.argv[1])
ws = wb.active
existing = set()
for row in ws.iter_rows(min_row=2, max_row=ws.max_row):
    m = re.match(r'(\\d+)', str(row[1].value or ''))
    if m: existing.add(m.group(1))
added = 0
nr = ws.max_row + 1
for p in data:
    if str(p['lc']) not in existing:
        ws.cell(row=nr, column=1, value='leetcode')
        ws.cell(row=nr, column=2, value=f"{p['lc']} - {p['title']}")
        ws.cell(row=nr, column=3, value=p.get('difficulty',''))
        ws.cell(row=nr, column=4, value=p.get('tags',''))
        ws.cell(row=nr, column=5, value=1)
        ws.cell(row=nr, column=6, value=p.get('date',''))
        nr += 1; added += 1
        existing.add(str(p['lc']))
wb.save(sys.argv[1])
print(json.dumps({'added': added}))
`;
  const result = execSync(`python3 -c '${script}' '${xlsxPath}'`,
    { input: pyData, encoding: 'utf8', maxBuffer: 10*1024*1024 });
  return JSON.parse(result.trim());
}

// ─── MD Tracker ─────────────────────────────────────────────

/** Extract LC numbers from MD tracker table rows. */
function extractMdLcNumbers(mdPath) {
  const content = fs.readFileSync(mdPath, 'utf8');
  const re = /^\|\s*\d+\s*\|[^|]+\|\s*(\d+)\s*\|/gm;
  const lcs = [];
  let m;
  while ((m = re.exec(content)) !== null) lcs.push(m[1]);
  return [...new Set(lcs)];
}

/** Convert LC numbers to title slugs via a lookup. */
function lcNumsToSlugs(lcNums, detailsMap) {
  const slugMap = new Map();
  for (const [slug, info] of detailsMap) {
    slugMap.set(info.lcNum, slug);
  }
  return lcNums.map(lc => slugMap.get(lc)).filter(Boolean);
}

/**
 * Remove solved problems from MD, add to company Excel.
 * solvedSet: Set of LC# strings that are confirmed solved.
 */
function processTracker(tracker, solvedSet, solvedInfo) {
  // solvedInfo: Map<lcNum, {title, difficulty, section}>
  const lines = fs.readFileSync(tracker.mdPath, 'utf8').split('\n');
  const re = /^\|\s*\d+\s*\|([^|]+)\|\s*(\d+)\s*\|([^|]+)\|\s*\[[ ]\]\s*\|([^|]*)\|/;

  const matched = [];
  const linesToRemove = new Set();
  let section = '';

  for (let i = 0; i < lines.length; i++) {
    const sec = lines[i].match(/^### (.+)/);
    if (sec) section = sec[1].replace(/\s*`\[.*\]`/, '').trim();
    const rm = lines[i].match(re);
    if (rm) {
      const lc = rm[2].trim();
      if (solvedSet.has(lc)) {
        linesToRemove.add(i);
        matched.push({ lc, title: rm[1].trim(), section, difficulty: rm[3].trim() });
      }
    }
  }

  // Write MD without solved rows
  if (linesToRemove.size > 0) {
    const newLines = lines.filter((_, i) => !linesToRemove.has(i));
    fs.writeFileSync(tracker.mdPath, newLines.join('\n'));
  }

  // Add to company Excel
  let excelAdded = 0;
  if (tracker.excelPath && matched.length > 0) {
    const pyData = JSON.stringify(matched.map(m => ({
      lc: m.lc, title: m.title, difficulty: m.difficulty, section: m.section
    })));
    const script = `
import openpyxl, json, sys
data = json.loads(sys.stdin.read())
wb = openpyxl.load_workbook(sys.argv[1])
ws = wb.active
existing = set()
for row in ws.iter_rows(min_row=2, max_row=ws.max_row):
    lc = str(row[3].value or '').strip()
    if lc: existing.add(lc)
added = 0
nr = ws.max_row + 1
for p in data:
    if p['lc'] not in existing:
        ws.cell(row=nr, column=1, value=p.get('section',''))
        ws.cell(row=nr, column=3, value=p['title'])
        ws.cell(row=nr, column=4, value=int(p['lc']))
        ws.cell(row=nr, column=5, value=p.get('difficulty',''))
        ws.cell(row=nr, column=6, value='Done')
        nr += 1; added += 1
wb.save(sys.argv[1])
print(added)
`;
    const result = execSync(`python3 -c '${script}' '${tracker.excelPath}'`,
      { input: pyData, encoding: 'utf8' });
    excelAdded = parseInt(result.trim()) || 0;
  }

  return { matched, removed: linesToRemove.size, excelAdded };
}

// ─── Exports ────────────────────────────────────────────────

module.exports = {
  ROOT_DIR, CACHE_FILE,
  loadConfig, loadState, saveState, getSession,
  fetchSubmissions, fetchProblemDetails, verifySolved,
  hasCache, loadCache, clearCache,
  updateGlobalXlsx, extractMdLcNumbers, processTracker,
  sleep,
};
