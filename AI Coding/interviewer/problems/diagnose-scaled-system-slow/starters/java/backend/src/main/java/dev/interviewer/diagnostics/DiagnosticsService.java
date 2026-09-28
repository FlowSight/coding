package dev.interviewer.diagnostics;
import java.util.List;
import org.springframework.stereotype.Service;
@Service
public class DiagnosticsService {
    private final ScaledSystemDiagnostics diagnostics = new ScaledSystemDiagnostics();
    public ScaledSystemDiagnostics.DiagnosticReport diagnose(List<ScaledSystemDiagnostics.ShardMetrics> shards) { return diagnostics.diagnose(shards); }
    public List<ScaledSystemDiagnostics.Hypothesis> rank(DiagnosticsController.RankingRequest request) { return diagnostics.rankHypotheses(request.shards(), request.dependencies()); }
}
