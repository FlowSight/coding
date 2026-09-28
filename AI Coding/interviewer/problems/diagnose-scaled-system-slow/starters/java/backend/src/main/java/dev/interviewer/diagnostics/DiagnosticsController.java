package dev.interviewer.diagnostics;
import java.util.List;
import org.springframework.web.bind.annotation.*;
@RestController @RequestMapping("/api/diagnostics") @CrossOrigin(origins = "http://localhost:5173")
public class DiagnosticsController {
    private final DiagnosticsService service;
    public DiagnosticsController(DiagnosticsService service) { this.service = service; }
    @PostMapping("/analyze")
    public ScaledSystemDiagnostics.DiagnosticReport analyze(@RequestBody List<ScaledSystemDiagnostics.ShardMetrics> shards) { return service.diagnose(shards); }
    @PostMapping("/hypotheses")
    public List<ScaledSystemDiagnostics.Hypothesis> hypotheses(@RequestBody RankingRequest request) { return service.rank(request); }
    public record RankingRequest(List<ScaledSystemDiagnostics.ShardMetrics> shards, List<ScaledSystemDiagnostics.DependencyMetrics> dependencies) {}
}
