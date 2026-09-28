'use strict';

const test = require('node:test');
const assert = require('node:assert/strict');
const { summarizeShards } = require('../src/services/diagnosticsService');

test('computes a request-weighted fleet average', () => {
  const result = summarizeShards([
    { shard: 'a', requests: 3, latencyMs: 100 },
    { shard: 'b', requests: 1, latencyMs: 300 }
  ]);
  assert.equal(result.averageLatencyMs, 150);
});

test('does not hide a hot shard behind the fleet average', () => {
  const result = summarizeShards([
    { shard: 'hot', requests: 1, latencyMs: 900 },
    { shard: 'healthy', requests: 99, latencyMs: 10 }
  ], 200);
  assert.deepEqual(result.hotShards, ['hot']);
});
