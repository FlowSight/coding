package dev.interviewer.events;
import java.util.List;
import org.springframework.web.bind.annotation.*;
@RestController @RequestMapping("/api/events") @CrossOrigin(origins="http://localhost:5173")
public class EventFilterController {
    private final EventFilterService service;
    public EventFilterController(EventFilterService service) { this.service = service; }
    @PostMapping("/filter") public List<DataEventFilter.DataEvent> filter(@RequestBody List<DataEventFilter.DataEvent> events) { return service.filter(events); }
    @PostMapping("/report") public DataEventFilter.FilterReport report(@RequestBody List<DataEventFilter.DataEvent> events) { return service.report(events); }
}
