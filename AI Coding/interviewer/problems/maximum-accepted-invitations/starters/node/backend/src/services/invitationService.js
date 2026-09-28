'use strict';

function validateGrid(grid) {
  if (!Array.isArray(grid)) throw new TypeError('grid must be an array');
  const width = grid[0]?.length ?? 0;
  for (const row of grid) {
    if (!Array.isArray(row) || row.length !== width) throw new TypeError('grid must be rectangular');
  }
}

function maximumInvitations(grid) {
  validateGrid(grid);
  const matchedBoyByGirl = Array(grid[0]?.length ?? 0).fill(-1);
  let count = 0;
  function augment(boy, seenGirls) {
    for (let girl = 0; girl < matchedBoyByGirl.length; girl += 1) {
      if (grid[boy][girl] !== 1 || seenGirls[girl]) continue;
      seenGirls[girl] = true;
      if (matchedBoyByGirl[girl] === -1) {
        matchedBoyByGirl[girl] = boy;
        return true;
      }
      // BUG: try rerouting the currently matched boy through an augmenting path.
    }
    return false;
  }
  for (let boy = 0; boy < grid.length; boy += 1) {
    if (augment(boy, Array(matchedBoyByGirl.length).fill(false))) count += 1;
  }
  return count;
}

function maximumInvitationsWithAssignments(_grid) {
  throw new Error('TODO(maximum-invitations-with-assignments): return count and selected pairs');
}

class IncrementalInvitationMatcher {
  constructor(boyCount, girlCount) {
    this.boyCount = boyCount;
    this.girlCount = girlCount;
    throw new Error('TODO(initialize-incremental-invitation-matcher): initialize matching state');
  }
  addCompatibility(_boy, _girl) {
    throw new Error('TODO(add-incremental-compatibility): validate and add an idempotent edge');
  }
  currentMatching() {
    throw new Error('TODO(read-current-incremental-matching): return a stable maximum assignment');
  }
}

module.exports = {
  maximumInvitations,
  maximumInvitationsWithAssignments,
  IncrementalInvitationMatcher
};
