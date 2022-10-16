//
// Created by Вячеслав Кривенко on 07.10.2022.
//

#ifndef VICTORIAM_MACRODEFINITIONS_HPP
#define VICTORIAM_MACRODEFINITIONS_HPP

#define VIDECL [[maybe_unused]]
#define VIREQOUT [[nodiscard]]

#define VISRCBEG namespace Vi {
#define VISRCEND }

#define BIND_EVENT_FN(fn) [this](auto&&...args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#endif //VICTORIAM_MACRODEFINITIONS_HPP
