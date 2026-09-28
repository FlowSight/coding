'use strict';

function isValidEvent(event) {
  return event !== null && typeof event === 'object' &&
    typeof event.id === 'string' && event.id.trim() !== '' &&
    Number.isFinite(event.timestamp) && event.timestamp >= 0 &&
    event.data !== null && typeof event.data === 'object' &&
    !Array.isArray(event.data);
}

function filterValidEvents(events) {
  if (!Array.isArray(events)) throw new TypeError('events must be an array');
  const byId = new Map();
  for (const event of events) {
    if (isValidEvent(event)) byId.set(event.id, event);
  }
  // BUG: Map replacement keeps the last duplicate, then sorting loses input order.
  return [...byId.values()].sort((a, b) => a.timestamp - b.timestamp);
}

function filterEventsWithRejections(_events) {
  throw new Error('TODO(filter-events-with-rejection-details): return accepted events and deterministic reasons');
}

function createEventFilterStream() {
  throw new Error('TODO(create-validated-event-stream): create an object-mode filtering stream');
}

module.exports = {
  isValidEvent,
  filterValidEvents,
  filterEventsWithRejections,
  createEventFilterStream
};
