package dev.interviewer.router;
import java.util.*;
public final class UrlRouter{
 private final Node root=new Node();
 public void add(String pattern,String handler){if(handler==null||handler.isBlank())throw new IllegalArgumentException("Handler must not be blank");Node node=root;for(String segment:segments(pattern)){if(segment.startsWith(":")){if(segment.length()==1)throw new IllegalArgumentException("Wildcard needs a name");if(node.wildcard==null){node.wildcard=new Node();node.wildcardName=segment.substring(1);}node=node.wildcard;}else node=node.staticChildren.computeIfAbsent(segment,ignored->new Node());}node.handler=handler;}
 public Optional<RouteMatch>match(String path){return match(root,segments(path),0,new LinkedHashMap<>());}
 private Optional<RouteMatch>match(Node node,String[]segments,int index,Map<String,String>parameters){if(index==segments.length)return node.handler==null?Optional.empty():Optional.of(new RouteMatch(node.handler,parameters));Node staticChild=node.staticChildren.get(segments[index]);if(staticChild!=null){
   // Seeded bug: a static dead end prevents wildcard backtracking.
   return match(staticChild,segments,index+1,parameters);}
  if(node.wildcard!=null){Map<String,String>next=new LinkedHashMap<>(parameters);next.put(node.wildcardName,segments[index]);return match(node.wildcard,segments,index+1,next);}return Optional.empty();}
 public boolean remove(String pattern){throw new UnsupportedOperationException("Implement Route Removal and Trie Pruning");}
 public static final class ConcurrentUrlRouter{public void add(String pattern,String handler){throw new UnsupportedOperationException("Implement Concurrent Route Updates");}public Optional<RouteMatch>match(String path){throw new UnsupportedOperationException("Implement Concurrent Route Updates");}public boolean remove(String pattern){throw new UnsupportedOperationException("Implement Concurrent Route Updates");}}
 public record RouteMatch(String handler,Map<String,String>parameters){public RouteMatch{parameters=Map.copyOf(parameters);}}
 private static final class Node{private final Map<String,Node>staticChildren=new HashMap<>();private Node wildcard;private String wildcardName;private String handler;}
 private static String[]segments(String value){if(value==null||!value.startsWith("/"))throw new IllegalArgumentException("Route must start with /");if(value.equals("/"))return new String[0];String normalized=value.endsWith("/")?value.substring(0,value.length()-1):value;return normalized.substring(1).split("/");}
}
