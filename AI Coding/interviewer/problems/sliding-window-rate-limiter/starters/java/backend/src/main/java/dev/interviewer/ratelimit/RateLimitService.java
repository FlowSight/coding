package dev.interviewer.ratelimit;
import java.time.Duration;import org.springframework.stereotype.Service;
@Service public class RateLimitService{
 private final SlidingWindowRateLimiter limiter=new SlidingWindowRateLimiter(2,Duration.ofSeconds(1));
 public Decision evaluate(long timestampMillis){return new Decision(limiter.allow(timestampMillis),timestampMillis);}
 public Decision evaluate(String key,long timestampMillis){return new Decision(limiter.allow(key,timestampMillis),timestampMillis);}
 public record Decision(boolean allowed,long timestampMillis){}
}
