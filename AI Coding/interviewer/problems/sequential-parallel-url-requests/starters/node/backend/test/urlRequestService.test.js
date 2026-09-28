'use strict';
const test = require('node:test');
const assert = require('node:assert/strict');
const { requestSequentially } = require('../src/services/urlRequestService');

test('waits for each request before starting the next', async () => {
  let active = 0;
  let maximumActive = 0;
  const results = await requestSequentially(['a', 'b'], async (url) => {
    active += 1;
    maximumActive = Math.max(maximumActive, active);
    await Promise.resolve();
    active -= 1;
    return url.toUpperCase();
  });
  assert.equal(maximumActive, 1);
  assert.deepEqual(results, ['A', 'B']);
});
test('deduplicates while preserving first-seen order', async () => {
  const calls = [];
  const results = await requestSequentially(['b', 'a', 'b'], async (url) => {
    calls.push(url);
    return `response:${url}`;
  });
  assert.deepEqual(calls, ['b', 'a']);
  assert.deepEqual(results, ['response:b', 'response:a']);
});
