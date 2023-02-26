import React, {useState} from 'react'
import "../App.css"


export default class Grid extends React.Component {

    
    constructor(props) {
        super(props);
        this.state = {
        value : 0
        };
    }

    render() {
      return <div className="box">
          {this.state.value}
      </div>;
    }



  }