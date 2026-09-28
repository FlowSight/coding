'use strict';

async function requestSequentially(urls, request) {
  if (!Array.isArray(urls)) throw new TypeError('urls must be an array');
  if (typeof request !== 'function') throw new TypeError('request must be a function');
  // BUG: sorting changes first-seen order, and duplicates are still requested.
  const scheduled = [...urls].sort();
  const results = [];
  for (const url of scheduled) results.push(await request(url));
  return results;
}

async function requestInParallel(_urls, _request) {
  throw new Error('TODO(request-distinct-urls-in-parallel): preserve stable result ordering');
}

async function requestUrls(_urls, _request, _options = {}) {
  throw new Error('TODO(request-urls-with-bounded-concurrency): report per-URL errors without losing successes');
}

module.exports = {
  requestSequentially,
  requestInParallel,
  requestUrls
};
