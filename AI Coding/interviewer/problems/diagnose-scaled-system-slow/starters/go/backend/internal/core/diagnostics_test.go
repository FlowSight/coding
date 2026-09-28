package core

import "testing"

func TestAggregateByShardPreservesHotShard(t *testing.T) {
	summaries := AggregateByShard([]MetricSample{
		{Shard: "cold", LatencyMS: 10, Requests: 100},
		{Shard: "hot", LatencyMS: 500, Requests: 100, Errors: 7},
	})
	if len(summaries) != 2 {
		t.Fatalf("AggregateByShard() returned %d summaries, want one per shard (2): %#v", len(summaries), summaries)
	}
	if summaries[1].Shard != "hot" || summaries[1].AverageLatencyMS != 500 {
		t.Fatalf("hot shard summary was hidden: %#v", summaries)
	}
}
