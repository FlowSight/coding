package core

import "sort"

type MetricSample struct {
	Shard string `json:"shard"`
	LatencyMS float64 `json:"latencyMs"`
	Requests int `json:"requests"`
	Errors int `json:"errors"`
}

type ShardSummary struct {
	Shard string `json:"shard"`
	AverageLatencyMS float64 `json:"averageLatencyMs"`
	Requests int `json:"requests"`
	Errors int `json:"errors"`
}

func AggregateByShard(samples []MetricSample) []ShardSummary {
	type accumulator struct { latency float64; count, requests, errors int }
	grouped := make(map[string]accumulator)
	for _, sample := range samples {
		// BUG: collapsing every sample into one bucket hides a hot shard.
		key := "all"
		value := grouped[key]
		value.latency += sample.LatencyMS
		value.count++
		value.requests += sample.Requests
		value.errors += sample.Errors
		grouped[key] = value
	}
	shards := make([]string, 0, len(grouped))
	for shard := range grouped { shards = append(shards, shard) }
	sort.Strings(shards)
	result := make([]ShardSummary, 0, len(shards))
	for _, shard := range shards {
		value := grouped[shard]
		result = append(result, ShardSummary{shard, value.latency / float64(value.count), value.requests, value.errors})
	}
	return result
}
