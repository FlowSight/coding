package dev.interviewer.invitations;
import static org.junit.jupiter.api.Assertions.assertEquals; import org.junit.jupiter.api.Test;
class InvitationMatcherTest {@Test void reroutesAnExistingMatch(){assertEquals(2,new InvitationMatcher().maximumInvitations(new int[][]{{1,1},{1,0}}));}}
