'use strict';
const express = require('express');
const {
  maximumInvitations,
  maximumInvitationsWithAssignments
} = require('../services/invitationService');

const invitationRouter = express.Router();
invitationRouter.post('/maximum', (req, res, next) => {
  try {
    res.json({ count: maximumInvitations(req.body.grid) });
  } catch (error) {
    next(error);
  }
});
invitationRouter.post('/maximum-with-assignments', (req, res, next) => {
  try {
    res.json(maximumInvitationsWithAssignments(req.body.grid));
  } catch (error) {
    next(error);
  }
});
module.exports = { invitationRouter };
