package httpapi

import ("net/http"; "github.com/gin-gonic/gin"; "interviewer/filter-invalid-data-events/backend/internal/core"; "interviewer/filter-invalid-data-events/backend/internal/service")

func NewRouter(events *service.EventService) *gin.Engine {
	router := gin.Default()
	router.POST("/api/events/filter", func(c *gin.Context) {
		var input []core.DataEvent
		if err := c.ShouldBindJSON(&input); err != nil { c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()}); return }
		c.JSON(http.StatusOK, events.Filter(input))
	})
	return router
}
