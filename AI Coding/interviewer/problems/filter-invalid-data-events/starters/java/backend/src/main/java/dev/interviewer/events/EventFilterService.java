package dev.interviewer.events;
import java.util.List;
import org.springframework.stereotype.Service;
@Service public class EventFilterService {
    private final DataEventFilter filter = new DataEventFilter();
    public List<DataEventFilter.DataEvent> filter(List<DataEventFilter.DataEvent> events) { return filter.filterValid(events); }
    public DataEventFilter.FilterReport report(List<DataEventFilter.DataEvent> events) { return filter.filterWithRejectionReasons(events); }
}
