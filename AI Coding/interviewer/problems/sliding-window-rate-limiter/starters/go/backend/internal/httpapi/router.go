package httpapi

import ("net/http"; "time"; "github.com/gin-gonic/gin"; "interviewer/sliding-window-rate-limiter/backend/internal/service")
type decisionRequest struct { At string `json:"at"` }
func NewRouter(limiter *service.LimiterService) *gin.Engine {
	router := gin.Default()
	router.POST("/api/limiter/allow", func(c *gin.Context) {
		var request decisionRequest
		if err := c.ShouldBindJSON(&request); err != nil { c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()}); return }
		at, err := time.Parse(time.RFC3339, request.At)
		if err != nil { c.JSON(http.StatusBadRequest, gin.H{"error": "at must be RFC3339"}); return }
		c.JSON(http.StatusOK, gin.H{"allowed": limiter.Allow(at)})
	})
	return router
}
