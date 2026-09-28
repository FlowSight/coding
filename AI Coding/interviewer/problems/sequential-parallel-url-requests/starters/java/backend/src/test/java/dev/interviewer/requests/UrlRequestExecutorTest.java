package dev.interviewer.requests;
import static org.junit.jupiter.api.Assertions.assertEquals;import java.util.List;import org.junit.jupiter.api.Test;
class UrlRequestExecutorTest{@Test void preservesDuplicatesAndOrder(){var urls=List.of("https://b.test","https://a.test","https://b.test");var responses=new UrlRequestExecutor().fetchSequential(urls,url->new UrlRequestExecutor.Response(url,200,"body"));assertEquals(urls,responses.stream().map(UrlRequestExecutor.Response::url).toList());}}
