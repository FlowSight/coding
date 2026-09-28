package httpapi

import ("net/http"; "github.com/gin-gonic/gin"; "interviewer/sequential-parallel-url-requests/backend/internal/service")
type requestBatch struct { URLs []string `json:"urls"` }
func NewRouter(requests *service.RequestService) *gin.Engine {
	router := gin.Default()
	router.POST("/api/requests/sequential", func(c *gin.Context) {
		var batch requestBatch
		if err := c.ShouldBindJSON(&batch); err != nil { c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()}); return }
		c.JSON(http.StatusOK, requests.Run(c.Request.Context(), batch.URLs))
	})
	return router
}
