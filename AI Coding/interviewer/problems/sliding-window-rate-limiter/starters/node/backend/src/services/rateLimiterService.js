'use strict';

class SlidingWindowRateLimiter {
  constructor(limit, windowMs, clock = Date.now) {
    if (!Number.isInteger(limit) || limit <= 0) throw new TypeError('limit must be a positive integer');
    if (!Number.isFinite(windowMs) || windowMs <= 0) throw new TypeError('windowMs must be positive');
    if (typeof clock !== 'function') throw new TypeError('clock must be a function');
    this.limit = limit;
    this.windowMs = windowMs;
    this.clock = clock;
    this.acceptedAt = [];
  }

  allow(now = this.clock()) {
    if (!Number.isFinite(now)) throw new TypeError('now must be finite');
    // BUG: timestamps exactly on the left-open boundary must also be evicted.
    while (this.acceptedAt.length > 0 && now - this.acceptedAt[0] > this.windowMs) {
      this.acceptedAt.shift();
    }
    if (this.acceptedAt.length >= this.limit) return false;
    this.acceptedAt.push(now);
    return true;
  }

  allowForKey(_key, _now = this.clock()) {
    throw new Error('TODO(allow-request-for-key): maintain an independent window per key');
  }

  cleanup(_now = this.clock()) {
    throw new Error('TODO(cleanup-inactive-rate-limit-keys): remove inactive key state');
  }

  async allowConcurrent(_key, _now = this.clock()) {
    throw new Error('TODO(allow-concurrent-request): serialize updates for the same key');
  }
}

module.exports = { SlidingWindowRateLimiter };
