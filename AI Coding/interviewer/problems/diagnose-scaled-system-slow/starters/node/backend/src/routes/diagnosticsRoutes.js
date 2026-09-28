'use strict';

const express = require('express');
const {
  summarizeShards,
  rankHypotheses,
  recommendProbes
} = require('../services/diagnosticsService');

const diagnosticsRouter = express.Router();

diagnosticsRouter.post('/summary', (req, res, next) => {
  try {
    res.json(summarizeShards(req.body.samples, req.body.thresholdMs));
  } catch (error) {
    next(error);
  }
});

diagnosticsRouter.post('/hypotheses', (req, res, next) => {
  try {
    res.json(rankHypotheses(req.body.summary));
  } catch (error) {
    next(error);
  }
});

diagnosticsRouter.post('/probes', (req, res, next) => {
  try {
    res.json(recommendProbes(req.body.hypotheses));
  } catch (error) {
    next(error);
  }
});

module.exports = { diagnosticsRouter };
