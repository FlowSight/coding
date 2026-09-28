'use strict';
const express = require('express');
const {
  requestSequentially,
  requestInParallel,
  requestUrls
} = require('../services/urlRequestService');

const requestRouter = express.Router();
const fetchText = async (url) => {
  const response = await fetch(url);
  return { url, status: response.status, body: await response.text() };
};

requestRouter.post('/sequential', async (req, res, next) => {
  try {
    res.json({ results: await requestSequentially(req.body.urls, fetchText) });
  } catch (error) {
    next(error);
  }
});
requestRouter.post('/parallel', async (req, res, next) => {
  try {
    res.json({ results: await requestInParallel(req.body.urls, fetchText) });
  } catch (error) {
    next(error);
  }
});
requestRouter.post('/bounded', async (req, res, next) => {
  try {
    res.json(await requestUrls(req.body.urls, fetchText, req.body.options));
  } catch (error) {
    next(error);
  }
});
module.exports = { requestRouter };
