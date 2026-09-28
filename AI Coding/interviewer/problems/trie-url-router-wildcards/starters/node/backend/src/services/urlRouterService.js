'use strict';

function segments(path) {
  if (typeof path !== 'string' || !path.startsWith('/')) throw new TypeError('path must start with /');
  return path.split('/').filter(Boolean);
}
function node() {
  return { static: new Map(), wildcard: null, wildcardName: null, handler: undefined };
}

class UrlRouter {
  constructor() {
    this.root = node();
  }
  add(pattern, handler) {
    let current = this.root;
    for (const segment of segments(pattern)) {
      if (segment.startsWith(':')) {
        current.wildcard ??= node();
        current.wildcardName = segment.slice(1);
        current = current.wildcard;
      } else {
        if (!current.static.has(segment)) current.static.set(segment, node());
        current = current.static.get(segment);
      }
    }
    current.handler = handler;
  }
  match(path) {
    const parts = segments(path);
    const walk = (current, index, params) => {
      if (index === parts.length) {
        return current.handler === undefined ? null : { handler: current.handler, params };
      }
      const preferred = current.static.get(parts[index]);
      if (preferred) {
        // BUG: if this branch dead-ends, the wildcard branch is never tried.
        return walk(preferred, index + 1, params);
      }
      if (!current.wildcard) return null;
      return walk(current.wildcard, index + 1, {
        ...params,
        [current.wildcardName]: decodeURIComponent(parts[index])
      });
    };
    return walk(this.root, 0, {});
  }
  remove(_pattern) {
    throw new Error('TODO(remove-route-and-prune-trie): remove a route and safely prune unused nodes');
  }
}

class ConcurrentUrlRouter {
  constructor(_router = new UrlRouter()) {
    throw new Error('TODO(initialize-atomic-route-snapshots): initialize consistent route snapshots');
  }
  async add(_pattern, _handler) {
    throw new Error('TODO(add-route-atomically): publish a route update atomically');
  }
  match(_path) {
    throw new Error('TODO(match-consistent-route-snapshot): read from one route snapshot');
  }
}

module.exports = { UrlRouter, ConcurrentUrlRouter };
