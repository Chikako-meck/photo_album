/* element の後に改行する */
let wrap_div element => <div> element </div>;

/* 数字を HTML 要素にする */
let i n => ReasonReact.stringToElement (string_of_int n);

/* 文字列を HTML 要素にする */
let s str => ReasonReact.stringToElement str;

/* 文字列のペアを HTML 要素にする */
let pair (date, category, url) => <tr> <td> (s date) </td> <td> (s category) </td> <td> <img src=url height="100px"/> </td> </tr>;

/* element を <hn> で囲む */
let wrap_h n element =>
switch n {
| 1 => <h1> element </h1>
| 2 => <h2> element </h2>
| 3 => <h3> element </h3>
| _ => <h4> element </h4>
};

/* event から値を取り出す */
let value_of_event event =>
  (ReactDOMRe.domElementToObj (ReactEventRe.Form.target event))##value;

let name_of_event event =>
  (ReactDOMRe.domElementToObj (ReactEventRe.Form.target event))##name;


/* image を表示する */
let show_image filename => <img src=filename />;
Js.log "This is console log";

module Photo = {
    type state = {category: string, filename: string, date: string, keyword_date: string, keyword_category: string, history: list (string, string, string)};
    let component = ReasonReact.statefulComponent "photo";
    let handleSelect event {ReasonReact.state}=> {
      let value =value_of_event event;
      ReasonReact.Update {...state, category: value};
    };
    let handleChange event {ReasonReact.state} => {
      let value = value_of_event event;
      ReasonReact.Update {...state, filename: value};
    };
    let handleSend _event {ReasonReact.state} => {
        let category = state.category;
        let file = state.filename;
        let date = state.date;
        ReasonReact.Update {...state, filename: "" , category: "food",
                            history: [(date, category, file), ...state.history]};
    };
    let handleDate event {ReasonReact.state} => {
        let date = value_of_event event;
        ReasonReact.Update {...state, date: date};
    };
    let handleKeyword_date event {ReasonReact.state} => {
        let keyword = value_of_event event;
        ReasonReact.Update {...state, keyword_date:keyword}
    };
    let handleKeyword_category event {ReasonReact.state} => {
        let keyword = value_of_event event;
        ReasonReact.Update {...state, keyword_category:keyword}
    };
    let showHistory history => {
        history
      |> List.map pair;
    };
    let make _children => {
        ...component,
        initialState: fun () => {category: "none", filename: "", date: "1970-01-01", keyword_date: "1970-01-01", keyword_category: "none", history:[]},
        render: fun {state, update} => {
            <div>
            (s "*Please input date, category and URL of image.")
            <br/>
            <br/>
            <form name="From" method="POST" action="/cgi-bin/insert.py">
            <table id="input">
            <tr>
            <td>
            (s "date: ")
            </td>
            <td>
            <input _type="date" name="date" value=state.date onChange=(update handleDate)/>
            </td>
            </tr>
            <tr>
            <td>
            (s "category: ")
            </td>
            <td>
            <select value=state.category onChange=(update handleSelect) name="category">
                <option value="food">(s "food")</option>
                <option value="landscape">(s "landscape")</option>
                <option value="animal">(s "animal")</option>
                <option value="friend">(s "friend")</option>
            </select>
            </td>
            </tr>
            <tr>
            <td>
            (s "FILE: ")
            </td>
            <td>
            <input _type="url" onChange=(update handleChange) value=state.filename name="filename"/>
            </td>
            </tr>
            </table>
            <br/>
            <input _type="submit" value="store" name="store" id="store"/>
            </form>
            <br/>
            <br/>
            <br/>
            (s "*Please input keyword(date or category) to search images")
            <br/>
            <br/>
            <form name="From" method="POST" action="/cgi-bin/search.py">
            (s "date: ")
            <input _type="date" name="keyword_date" value=state.keyword_date onChange=(update handleKeyword_date)/>
            <br/>
            (s "category: ")
            <select value=state.keyword_category onChange=(update handleKeyword_category) name="keyword_category">
                <option value="none">(s "none")</option>
                <option value="food">(s "food")</option>
                <option value="landscape">(s "landscape")</option>
                <option value="animal">(s "animal")</option>
                <option value="friend">(s "friend")</option>
            </select>
            <br/>
            <input _type="submit" value="search" name="search" id="search"/>
            </form>
            </div>
        }
    };
};

ReactDOMRe.renderToElementWithId
    <div>
    (wrap_h 1 (s "Photo Album"))
    <hr/>
    <br/>
    <Photo />
    </div>
    "index";
