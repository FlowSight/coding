'use strict';
const express = require('express');
const { eventRouter } = require('./routes/eventRoutes');

function createApp() {
  const app = express();
  app.use(express.json());
  app.get('/api/health', (_req, res) => res.json({ status: 'ok' }));
  app.use('/api/events', eventRouter);
  app.use((error, _req, res, _next) => res
    .status(error instanceof TypeError ? 400 : 501)
    .json({ error: error.message }));
  return app;
}
module.exports = { createApp };
