package dev.interviewer.diagnostics;
import static org.junit.jupiter.api.Assertions.assertEquals;
import java.util.List;
import org.junit.jupiter.api.Test;
class ScaledSystemDiagnosticsTest {
    @Test void isolatesLowVolumeHotShard() {
        var diagnostics = new ScaledSystemDiagnostics();
        var shards = List.of(new ScaledSystemDiagnostics.ShardMetrics("healthy", 10_000, 20, 25, 0), new ScaledSystemDiagnostics.ShardMetrics("hot", 2, 2_000, 99, 1));
        assertEquals(List.of("hot"), diagnostics.diagnose(shards).hotShardIds());
    }
}
