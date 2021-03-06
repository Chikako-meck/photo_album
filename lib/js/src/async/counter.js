// Generated by BUCKLESCRIPT VERSION 1.8.1, PLEASE EDIT WITH CARE
'use strict';

var Block       = require("bs-platform/lib/js/block.js");
var Curry       = require("bs-platform/lib/js/curry.js");
var React       = require("react");
var Pervasives  = require("bs-platform/lib/js/pervasives.js");
var ReasonReact = require("reason-react/lib/js/src/reasonReact.js");

function increaseCount(_, param) {
  var state = param[/* state */3];
  return /* Update */Block.__(0, [/* record */[
              /* count */state[/* count */0] + 1 | 0,
              /* timerId */state[/* timerId */1]
            ]]);
}

var component = ReasonReact.statefulComponent("Counter");

function make() {
  var newrecord = component.slice();
  newrecord[/* didMount */4] = (function (param) {
      return /* SilentUpdate */Block.__(1, [/* record */[
                  /* count */param[/* state */3][/* count */0],
                  /* timerId : Some */[setInterval(Curry._1(param[/* update */2], increaseCount), 1000)]
                ]]);
    });
  newrecord[/* render */9] = (function (param) {
      return React.createElement("div", undefined, Pervasives.string_of_int(param[/* state */3][/* count */0]));
    });
  newrecord[/* initialState */10] = (function () {
      return /* record */[
              /* count */0,
              /* timerId : None */0
            ];
    });
  return newrecord;
}

exports.increaseCount = increaseCount;
exports.component     = component;
exports.make          = make;
/* component Not a pure module */
