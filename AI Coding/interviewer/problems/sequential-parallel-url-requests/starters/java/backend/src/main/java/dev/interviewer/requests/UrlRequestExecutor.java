package dev.interviewer.requests;
import java.util.*;
public final class UrlRequestExecutor{
 public List<Response> fetchSequential(List<String> urls,UrlFetcher fetcher){requireInputs(urls,fetcher);Map<String,Response> responsesByUrl=new HashMap<>();for(String url:urls){try{responsesByUrl.put(url,fetcher.fetch(url));}catch(Exception e){throw new RequestFailedException(url,e);}}
  // Seeded bug: map storage removes duplicates and loses input order.
  return new ArrayList<>(responsesByUrl.values());}
 public List<Response> fetchParallel(List<String> urls,UrlFetcher fetcher){throw new UnsupportedOperationException("Implement Parallel URL Fetching");}
 public List<FetchResult> fetchParallel(List<String> urls,UrlFetcher fetcher,int maxConcurrency){throw new UnsupportedOperationException("Implement Bounded Concurrency and Error Policy");}
 @FunctionalInterface public interface UrlFetcher{Response fetch(String url)throws Exception;}
 public record Response(String url,int statusCode,String body){}
 public record FetchResult(String url,Response response,Throwable error){public boolean succeeded(){return error==null;}}
 public static final class RequestFailedException extends RuntimeException{private final String url;public RequestFailedException(String url,Throwable cause){super("Request failed: "+url,cause);this.url=url;}public String url(){return url;}}
 private static void requireInputs(List<String>urls,UrlFetcher fetcher){if(urls==null||fetcher==null||urls.stream().anyMatch(Objects::isNull))throw new IllegalArgumentException("URLs and fetcher must not be null");}
}
