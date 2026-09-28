package core

type Hypothesis struct {
	Name string `json:"name"`
	Score float64 `json:"score"`
	Evidence []string `json:"evidence"`
}

func RankHypotheses(summaries []ShardSummary) []Hypothesis {
	// TODO(rank-diagnostic-hypotheses): rank likely causes using observed shard evidence.
	return nil
}

type Probe struct {
	Name string `json:"name"`
	Rationale string `json:"rationale"`
}

func RecommendProbes(hypotheses []Hypothesis) []Probe {
	// TODO(recommend-observability-probe): recommend targeted probes in priority order.
	return nil
}
