'use strict';

const express = require('express');
const {
  filterValidEvents,
  filterEventsWithRejections
} = require('../services/eventFilterService');

const eventRouter = express.Router();
eventRouter.post('/filter', (req, res, next) => {
  try {
    res.json({ events: filterValidEvents(req.body.events) });
  } catch (error) {
    next(error);
  }
});
eventRouter.post('/filter-with-rejections', (req, res, next) => {
  try {
    res.json(filterEventsWithRejections(req.body.events));
  } catch (error) {
    next(error);
  }
});

module.exports = { eventRouter };
