package dev.interviewer.ratelimit;
import java.time.Duration;import java.util.*;
public final class SlidingWindowRateLimiter{
 private final int limit;private final long windowMillis;private final Deque<Long>accepted=new ArrayDeque<>();private final Map<String,Deque<Long>>acceptedByKey=new HashMap<>();
 public SlidingWindowRateLimiter(int limit,Duration window){if(limit<=0||window==null||window.isZero()||window.isNegative())throw new IllegalArgumentException("Limit and window must be positive");this.limit=limit;windowMillis=window.toMillis();if(windowMillis==0)throw new IllegalArgumentException("Window must be at least one millisecond");}
 public boolean allow(long timestampMillis){long cutoff=timestampMillis-windowMillis;
  // Seeded bug: an event exactly at the cutoff is retained.
  while(!accepted.isEmpty()&&accepted.peekFirst()<cutoff)accepted.removeFirst();if(accepted.size()>=limit)return false;accepted.addLast(timestampMillis);return true;}
 public boolean allow(String key,long timestampMillis){throw new UnsupportedOperationException("Implement Enforce Per-Key Rate Limits");}
 public int cleanup(long timestampMillis){throw new UnsupportedOperationException("Implement Clean Up Stale Keys Safely");}
 public int trackedKeyCount(){return acceptedByKey.size();}
}
