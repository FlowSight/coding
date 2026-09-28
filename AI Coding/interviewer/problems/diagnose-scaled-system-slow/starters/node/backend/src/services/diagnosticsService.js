'use strict';

function summarizeShards(samples, thresholdMs = 200) {
  if (!Array.isArray(samples)) throw new TypeError('samples must be an array');
  let requests = 0;
  let weightedLatency = 0;
  for (const sample of samples) {
    if (!sample || typeof sample.shard !== 'string' ||
        !Number.isFinite(sample.requests) || sample.requests < 0 ||
        !Number.isFinite(sample.latencyMs) || sample.latencyMs < 0) {
      throw new TypeError('invalid sample');
    }
    requests += sample.requests;
    weightedLatency += sample.requests * sample.latencyMs;
  }
  const averageLatencyMs = requests === 0 ? 0 : weightedLatency / requests;
  return {
    requests,
    averageLatencyMs,
    // BUG: a fleet-wide average can hide one hot shard.
    hotShards: averageLatencyMs >= thresholdMs ? ['all'] : []
  };
}

function rankHypotheses(_summary) {
  throw new Error('TODO(rank-diagnostic-hypotheses): rank likely causes with supporting evidence');
}

function recommendProbes(_hypotheses) {
  throw new Error('TODO(recommend-observability-probes): recommend targeted probes without duplicates');
}

module.exports = {
  summarizeShards,
  rankHypotheses,
  recommendProbes
};
