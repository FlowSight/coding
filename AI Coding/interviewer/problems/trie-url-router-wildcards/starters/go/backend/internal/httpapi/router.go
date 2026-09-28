package httpapi

import ("net/http"; "github.com/gin-gonic/gin"; "interviewer/trie-url-router-wildcards/backend/internal/service")
type routeRequest struct { Pattern string `json:"pattern"`; Handler string `json:"handler"` }
func NewRouter(routes *service.RouteService) *gin.Engine {
	router := gin.Default()
	router.POST("/api/routes", func(c *gin.Context) {
		var request routeRequest
		if err := c.ShouldBindJSON(&request); err != nil { c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()}); return }
		routes.Add(request.Pattern, request.Handler)
		c.Status(http.StatusCreated)
	})
	router.GET("/api/routes/match", func(c *gin.Context) { c.JSON(http.StatusOK, routes.Match(c.Query("path"))) })
	return router
}
