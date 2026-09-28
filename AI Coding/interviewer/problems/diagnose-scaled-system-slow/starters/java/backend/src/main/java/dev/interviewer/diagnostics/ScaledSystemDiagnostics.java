package dev.interviewer.diagnostics;
import java.util.List;
public final class ScaledSystemDiagnostics {
    public DiagnosticReport diagnose(List<ShardMetrics> shards) {
        if (shards == null || shards.isEmpty()) return new DiagnosticReport(0.0, List.of());
        long totalRequests = 0; double weightedLatency = 0.0;
        for (ShardMetrics shard : shards) { validate(shard); totalRequests += shard.requestCount(); weightedLatency += shard.p99LatencyMillis() * shard.requestCount(); }
        double aggregateLatency = totalRequests == 0 ? 0.0 : weightedLatency / totalRequests;
        // Seeded bug: the aggregate masks a low-volume hot shard.
        List<String> hotShards = aggregateLatency >= 500.0 ? shards.stream().map(ShardMetrics::shardId).toList() : List.of();
        return new DiagnosticReport(aggregateLatency, hotShards);
    }
    public List<Hypothesis> rankHypotheses(List<ShardMetrics> shards, List<DependencyMetrics> dependencies) { throw new UnsupportedOperationException("Implement Rank Diagnostic Hypotheses"); }
    public List<Probe> recommendProbes(List<Hypothesis> rankedHypotheses) { throw new UnsupportedOperationException("Implement Recommend the Next Observability Probe"); }
    public record ShardMetrics(String shardId, long requestCount, double p99LatencyMillis, double cpuPercent, long errorCount) {}
    public record DependencyMetrics(String name, double p99LatencyMillis, double errorRate) {}
    public record DiagnosticReport(double aggregateLatencyMillis, List<String> hotShardIds) { public DiagnosticReport { hotShardIds = List.copyOf(hotShardIds); } }
    public record Hypothesis(String name, double score, String evidence) {}
    public record Probe(String name, String purpose) {}
    private static void validate(ShardMetrics shard) {
        if (shard == null || shard.shardId() == null || shard.shardId().isBlank()) throw new IllegalArgumentException("Every shard needs an id");
        if (shard.requestCount() < 0 || shard.errorCount() < 0) throw new IllegalArgumentException("Counts must be non-negative");
    }
}
