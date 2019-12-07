package fs

import "github.com/astaxie/beego/httplib"

func (c *Client) Download(url, filename string) error {
	req := httplib.Get(url)
	return req.ToFile(filename)
}
