// https://egghead.io/lessons/node-js-intro-to-web-scraping-with-node-and-x-ray
var Xray  = require("x-ray");

var xray = new Xray();


// https://egghead.io/lessons/node-js-intro-to-web-scraping-with-node-and-x-ray
var Xray  = require("x-ray");

var xray = new Xray();
var html = 'http://www.bonappetit.com/recipe/giant-chocolate-chip-skillet-cookie';

// // xray(html,'body')(function(){
// // 	console.log(title);
// // });
// xray(html,'li'), items:xray('.ingredients',
// 	[{
// 			name:'.name',
// 			quantity:'.quantity',
// 			unit:'.unit',
// 	}]);
// // xray(html, '.ingredients')(console.log)
// 	.write('results.json');

// x(html, '.item', [{
//   title: 'h2',
//   tags: x('.tags', ['li'])
// }])(console.log)


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


// 	{	items: xray(['li'], 
// 		{
// 			ugh: xray(['span'], 
// 					{ list: xray('.ingredients',
// 						[{
// 							name: '.name',//,
// 							quantity:'.quantity',
// 							unit:'.unit'
// 						}])
// 				  })
// 		})
		
// })//(console.log)
// 	.write('results.json');


// rd1
// xray('http://www.bonappetit.com/recipe/giant-chocolate-chip-skillet-cookie', 
// 	{class: 'ingredients', items: xray('.ingredients',
// 	[{
// 			name:'.name',
// 			quantity:'.quantity',
// 			unit:'.unit',
// 	}])})
// 	.write('results.json');

//rd 2
// xray('http://www.bonappetit.com/recipe/giant-chocolate-chip-skillet-cookie','li',['span'], //['.ingredients']
// 	{	items: xray(
// 		[{
// 			name: '.name',
// 	// { items: xray('.ingredient',
// 	// [{
// 	// 		name:'.name',
// 			quantity:'.quantity',
// 			unit:'.unit'
// 	// }])}
// 		}]
// )})//(console.log)
// 	.write('results.json');




