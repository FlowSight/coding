package dev.interviewer.ratelimit;
import org.springframework.web.bind.annotation.*;
@RestController @RequestMapping("/api/rate-limit") @CrossOrigin(origins="http://localhost:5173")
public class RateLimitController{
 private final RateLimitService service;public RateLimitController(RateLimitService service){this.service=service;}
 @PostMapping("/check")public RateLimitService.Decision check(@RequestBody CheckRequest request){return service.evaluate(request.timestampMillis());}
 @PostMapping("/check-key")public RateLimitService.Decision checkKey(@RequestBody CheckRequest request){return service.evaluate(request.key(),request.timestampMillis());}
 public record CheckRequest(String key,long timestampMillis){}
}
