package httpapi

import (
	"net/http"
	"github.com/gin-gonic/gin"
	"interviewer/diagnose-scaled-system-slow/backend/internal/core"
	"interviewer/diagnose-scaled-system-slow/backend/internal/service"
)

func NewRouter(diagnostics *service.DiagnosticsService) *gin.Engine {
	router := gin.Default()
	router.POST("/api/diagnostics/summarize", func(c *gin.Context) {
		var samples []core.MetricSample
		if err := c.ShouldBindJSON(&samples); err != nil {
			c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
			return
		}
		c.JSON(http.StatusOK, diagnostics.Summarize(samples))
	})
	return router
}
