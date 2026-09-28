'use strict';

const express = require('express');
const { SlidingWindowRateLimiter } = require('../services/rateLimiterService');

const rateLimitRouter = express.Router();
const limiter = new SlidingWindowRateLimiter(3, 1000);

rateLimitRouter.post('/check', (req, res, next) => {
  try {
    res.json({ allowed: limiter.allow(req.body.now) });
  } catch (error) {
    next(error);
  }
});
rateLimitRouter.post('/keys/:key/check', (req, res, next) => {
  try {
    res.json({ allowed: limiter.allowForKey(req.params.key, req.body.now) });
  } catch (error) {
    next(error);
  }
});
rateLimitRouter.post('/cleanup-inactive-keys', (req, res, next) => {
  try {
    res.json({ removed: limiter.cleanup(req.body.now) });
  } catch (error) {
    next(error);
  }
});

module.exports = { rateLimitRouter };
