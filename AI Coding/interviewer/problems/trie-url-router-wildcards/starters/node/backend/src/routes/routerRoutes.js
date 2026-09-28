'use strict';
const express = require('express');
const { UrlRouter } = require('../services/urlRouterService');
const routerRoutes = express.Router();
const urlRouter = new UrlRouter();

routerRoutes.post('/routes', (req, res, next) => {
  try {
    urlRouter.add(req.body.pattern, req.body.handler);
    res.status(201).json({ added: true });
  } catch (error) {
    next(error);
  }
});
routerRoutes.get('/match', (req, res, next) => {
  try {
    res.json({ match: urlRouter.match(req.query.path) });
  } catch (error) {
    next(error);
  }
});
routerRoutes.delete('/routes', (req, res, next) => {
  try {
    res.json({ removed: urlRouter.remove(req.body.pattern) });
  } catch (error) {
    next(error);
  }
});
module.exports = { routerRoutes };
