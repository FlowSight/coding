package httpapi

import ("net/http"; "github.com/gin-gonic/gin"; "interviewer/maximum-accepted-invitations/backend/internal/service")

type matchingRequest struct { Grid [][]int `json:"grid"` }
func NewRouter(matching *service.MatchingService) *gin.Engine {
	router := gin.Default()
	router.POST("/api/invitations/maximum", func(c *gin.Context) {
		var request matchingRequest
		if err := c.ShouldBindJSON(&request); err != nil { c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()}); return }
		c.JSON(http.StatusOK, gin.H{"count": matching.Maximum(request.Grid)})
	})
	return router
}
