package dev.interviewer.requests;
import java.util.List;import org.springframework.web.bind.annotation.*;
@RestController @RequestMapping("/api/requests") @CrossOrigin(origins="http://localhost:5173")
public class RequestExecutionController{
 private final RequestExecutionService service;public RequestExecutionController(RequestExecutionService service){this.service=service;}
 @PostMapping("/sequential")public List<UrlRequestExecutor.Response>sequential(@RequestBody UrlBatch batch){return service.sequential(batch.urls());}
 @PostMapping("/parallel")public List<UrlRequestExecutor.Response>parallel(@RequestBody UrlBatch batch){return service.parallel(batch.urls());}
 public record UrlBatch(List<String>urls){}
}
