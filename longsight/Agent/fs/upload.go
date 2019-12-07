package fs

import (
	"github.com/astaxie/beego/httplib"
)

type Client struct {
	URL string
}

func NewClient(url string) *Client {
	return &Client{URL: url}
}

func (c *Client) Upload(filepath string) (*ResponseUpload, error) {
	var res ResponseUpload
	req := httplib.Post(c.URL)
	req.PostFile("file", filepath)
	req.Param("output", "json")
	req.Param("scene", "")
	req.Param("path", "LongSight")
	err := req.ToJSON(&res)
	return &res, err
}

type ResponseUpload struct {
	URL     string `json:"url"`
	MD5     string `json:"md5"`
	Path    string `json:"path"`
	Domain  string `json:"domain"`
	Scene   string `json:"scene"`
	Size    int    `json:"size"`
	ModTime int    `json:"mtime"`
	Scenes  string `json:"scenes"`
	Retmsg  string `json:"retmsg"`
	Retcode int    `json:"retcode"`
	Src     string `json:"src"`
}
