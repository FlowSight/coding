'use strict';
const test = require('node:test');
const assert = require('node:assert/strict');
const { filterValidEvents } = require('../src/services/eventFilterService');

test('rejects malformed events', () => {
  const valid = { id: 'ok', timestamp: 1, data: { value: 1 } };
  assert.deepEqual(filterValidEvents([
    null,
    { id: '', timestamp: 1, data: {} },
    { id: 'bad-time', timestamp: Number.NaN, data: {} },
    { id: 'bad-data', timestamp: 1, data: [] },
    valid
  ]), [valid]);
});

test('keeps first duplicates in stable input order', () => {
  const firstB = { id: 'b', timestamp: 20, data: { version: 1 } };
  const firstA = { id: 'a', timestamp: 10, data: { version: 1 } };
  const duplicateB = { id: 'b', timestamp: 5, data: { version: 2 } };
  assert.deepEqual(filterValidEvents([firstB, firstA, duplicateB]), [firstB, firstA]);
});
