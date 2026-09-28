'use strict';
const test = require('node:test');
const assert = require('node:assert/strict');
const { SlidingWindowRateLimiter } = require('../src/services/rateLimiterService');

test('rejects requests while the active window is full', () => {
  const limiter = new SlidingWindowRateLimiter(2, 1000);
  assert.equal(limiter.allow(100), true);
  assert.equal(limiter.allow(200), true);
  assert.equal(limiter.allow(999), false);
});

test('evicts a request exactly at the window boundary', () => {
  const limiter = new SlidingWindowRateLimiter(1, 1000);
  assert.equal(limiter.allow(100), true);
  assert.equal(limiter.allow(1100), true);
});
