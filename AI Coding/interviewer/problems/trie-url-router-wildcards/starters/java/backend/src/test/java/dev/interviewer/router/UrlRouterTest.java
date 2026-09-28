package dev.interviewer.router;
import static org.junit.jupiter.api.Assertions.*;import org.junit.jupiter.api.Test;
class UrlRouterTest{@Test void backtracksFromStaticDeadEnd(){var router=new UrlRouter();router.add("/users/new/settings","settings");router.add("/users/:id/profile","profile");var match=router.match("/users/new/profile");assertTrue(match.isPresent());assertEquals("profile",match.orElseThrow().handler());assertEquals("new",match.orElseThrow().parameters().get("id"));}}
