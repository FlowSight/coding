package dev.interviewer.events;
import static org.junit.jupiter.api.Assertions.assertEquals;
import java.util.List;
import org.junit.jupiter.api.Test;
class DataEventFilterTest {
    @Test void preservesValidFirstOccurrencesInInputOrder() {
        var filter = new DataEventFilter();
        var firstB = new DataEventFilter.DataEvent("b","click","first-b",1);
        var firstA = new DataEventFilter.DataEvent("a","click","first-a",2);
        assertEquals(List.of(firstB, firstA), filter.filterValid(List.of(firstB, firstA, new DataEventFilter.DataEvent("b","click","second-b",3), new DataEventFilter.DataEvent(" ","click","invalid",4))));
    }
}
