var express = require('express');
var router = express.Router();

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index', { title: 'Expression~~' });
});

router.post('/do-authentication',function(req,res,next){
  if(req.body.id === 'test' && req.body.pswd === 'test') {
    // set session infoS
    req.session.authenticated = true;
    // pop up and redirect
    res.send('<script type="text/javascript">alert("Hi me!!");window.location.href="/secure"</script>');
  } else {
    res.send('<script type="text/javascript">alert("you are not me.. right?");window.location.href = "/";</script>');
  }
});

module.exports = router;
