package dev.interviewer.events;
import java.util.*;
import java.util.function.Consumer;
public final class DataEventFilter {
    public List<DataEvent> filterValid(List<DataEvent> events) {
        if (events == null) throw new IllegalArgumentException("Events must not be null");
        Map<String, DataEvent> byId = new TreeMap<>();
        for (DataEvent event : events) {
            if (event == null || event.id() == null || event.payload() == null) continue;
            // Seeded bugs: blank ids pass, the last duplicate wins, and output is sorted.
            byId.put(event.id(), event);
        }
        return new ArrayList<>(byId.values());
    }
    public FilterReport filterWithRejectionReasons(List<DataEvent> events) { throw new UnsupportedOperationException("Implement Report Rejection Details"); }
    public StreamingFilter newStreamingFilter(Consumer<DataEvent> accepted) { throw new UnsupportedOperationException("Implement Stream Validated Events"); }
    public record DataEvent(String id, String type, String payload, long timestampMillis) {}
    public enum RejectionReason { NULL_EVENT, MISSING_ID, MISSING_TYPE, MISSING_PAYLOAD, DUPLICATE_ID }
    public record RejectedEvent(DataEvent event, RejectionReason reason) {}
    public record FilterReport(List<DataEvent> accepted, List<RejectedEvent> rejected) { public FilterReport { accepted = List.copyOf(accepted); rejected = List.copyOf(rejected); } }
    public interface StreamingFilter extends AutoCloseable { void accept(DataEvent event); Collection<RejectedEvent> rejected(); void close(); }
}
