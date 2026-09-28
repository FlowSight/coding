'use strict';
const test = require('node:test');
const assert = require('node:assert/strict');
const { UrlRouter } = require('../src/services/urlRouterService');

test('matches static and wildcard routes', () => {
  const router = new UrlRouter();
  router.add('/health', 'health');
  router.add('/users/:id', 'user');
  assert.deepEqual(router.match('/health'), { handler: 'health', params: {} });
  assert.deepEqual(router.match('/users/42'), { handler: 'user', params: { id: '42' } });
});
test('backtracks from a dead static branch to a wildcard', () => {
  const router = new UrlRouter();
  router.add('/files/static/info', 'static-info');
  router.add('/files/:name/download', 'download');
  assert.deepEqual(router.match('/files/static/download'), {
    handler: 'download',
    params: { name: 'static' }
  });
});
