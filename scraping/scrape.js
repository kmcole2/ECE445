/*
	Brief Tutorial 			--		https://egghead.io/lessons/node-js-intro-to-web-scraping-with-node-and-x-ray
	
	Xray documentation	-- 		https://github.com/lapwinglabs/x-ray

	To scrape ingredients for bonappetit recipes

 	How to run? (assuming you have node)
	  > node scrape.js
	  results will be output to 'results.json' file
 */
var Xray  = require("x-ray");
var xray = new Xray();
var html = 'http://www.bonappetit.com/recipe/giant-chocolate-chip-skillet-cookie';

xray(html, '.ingredients', [{ 
	  ingredients: xray(['span'],'li', [{
				name: '.name',
				quantity:'.quantity',
				unit:'.unit'	 
	  }])
}]
)
// (console.log)
.write('results.json');
