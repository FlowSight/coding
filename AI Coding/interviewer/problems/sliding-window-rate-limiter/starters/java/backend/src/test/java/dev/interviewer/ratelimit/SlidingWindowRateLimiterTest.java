package dev.interviewer.ratelimit;
import static org.junit.jupiter.api.Assertions.assertTrue;import java.time.Duration;import org.junit.jupiter.api.Test;
class SlidingWindowRateLimiterTest{@Test void acceptsAtExactBoundary(){var limiter=new SlidingWindowRateLimiter(2,Duration.ofMillis(1000));assertTrue(limiter.allow(0));assertTrue(limiter.allow(500));assertTrue(limiter.allow(1000));}}
