'use strict';
const test = require('node:test');
const assert = require('node:assert/strict');
const { maximumInvitations } = require('../src/services/invitationService');

test('handles empty and straightforward inputs', () => {
  assert.equal(maximumInvitations([]), 0);
  assert.equal(maximumInvitations([[1, 0], [0, 1]]), 2);
});
test('reroutes an earlier match along an augmenting path', () => {
  assert.equal(maximumInvitations([[1, 1], [1, 0]]), 2);
});
